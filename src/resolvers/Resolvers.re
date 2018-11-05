type pubsub;

/* working around the type system to call the publish method on the pubsub object created in the index.js file. */

let publish: (pubsub, Schema.state) => unit = [%bs.raw
  {|(pubsub, serializableState) => { pubsub.publish("STATE", serializableState)}|}
];

/*
 subscription is defined in a JS module so we need this next code block to access it in ReasonML.
 We don't work with the subscription object directly in Reason so its defined as a abstract type.
 */

type stateAsyncIterator;
[@bs.val] [@bs.module "./Subscription"]
external subscriptions : stateAsyncIterator = "";

/*
  We take pubsub as a dependency here. "init" is called in the index.js file and passed a pubsub value.
  Since we don't work with the pubsub value directly in Reason we are defining it as an abstract type.
 */

let serialize: State.state => Schema.state =
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

let init = (pubsub: pubsub) => {
  let store = Store.create(Reducer.reducer, State.initialState);
  let _unsubscribe =
    Store.subscribe(store, state => publish(pubsub, serialize(state)));

  {
    /* here we are passing the store as a dependency to the resolvers */
    "Query": Query.resolvers(store),
    "Mutation": Mutation.resolvers(store),
    "Subscription": subscriptions,
  };
};