/**
 * We will only need a single subscription. This subscription push a stream of states to the client.
 * Since our application will only be accessed locally we don't need to think about optimizations or latency.
 */

module.exports.subscriptions = {
  state: {
    subscribe: (_root, _args, { pubsub }) => pubsub.asyncIterator(`STATE`)
  }
};
