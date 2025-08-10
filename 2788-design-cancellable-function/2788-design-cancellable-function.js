function cancellable(generator) {
    let finished = false;
    let cancelRequested = false;
    let currentReject = null;
    let resolvePromise, rejectPromise;
    const promise = new Promise((resolve, reject) => {
        resolvePromise = resolve;
        rejectPromise = reject;
    });

    const cancel = () => {
        if (finished || cancelRequested) return;
        cancelRequested = true;
        if (currentReject) {
            currentReject("Cancelled");
        }
    };

    async function run() {
        try {
            let next = generator.next();
            while (!next.done) {
                if (cancelRequested) {
                    try {
                        next = generator.throw("Cancelled");
                    } catch (err) {
                        throw err;
                    }
                    continue;
                }

                try {
                    let rejectCurrent;
                    const cancelPromise = new Promise((_, reject) => {
                        rejectCurrent = reject;
                    });
                    currentReject = rejectCurrent;
                    const value = await Promise.race([next.value, cancelPromise]);
                    currentReject = null;
                    try {
                        next = generator.next(value);
                    } catch (err) {
                        throw err;
                    }
                } catch (err) {
                    currentReject = null;
                    try {
                        next = generator.throw(err);
                    } catch (innerErr) {
                        throw innerErr;
                    }
                }
            }
            resolvePromise(next.value);
        } catch (err) {
            rejectPromise(err);
        } finally {
            finished = true;
        }
    }

    run();
    return [cancel, promise];
}