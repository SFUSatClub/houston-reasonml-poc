open Schema;

let resolvers: PubSub.t => subscription =
  pubsub => {
    "state": {
      "subscribe": () => PubSub.asyncIterator(pubsub, "STATE"),
    },
  };

let mapToSchemaState: State.state => Schema.state =
  ({uplink}) => {
    open State;
    let {sequenceId, pending, unresolved, successful, failed, inProgress} = uplink;
    {
      "state": {
        "uplink": {
          "sequenceId": Js.Nullable.fromOption(sequenceId),
          "pending": Array.of_list(pending),
          "unresolved": Array.of_list(unresolved),
          "successful": Array.of_list(successful),
          "failed": Array.of_list(failed),
          "inProgress": inProgress,
        },
      },
    };
  };