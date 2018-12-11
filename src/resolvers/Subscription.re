open Schema;

let resolvers: PubSub.t => subscription =
  pubsub => {
    "state": {
      "subscribe": () => PubSub.asyncIterator(pubsub, "STATE"),
    },
  };