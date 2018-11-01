module.exports.subscriptions = {
  state: {
    subscribe: (_root, _args, { pubsub }) => pubsub.asyncIterator(`STATE`)
  }
};
