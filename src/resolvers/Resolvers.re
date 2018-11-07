/*
  We take pubsub as a dependency here. "init" is called in the index.js file and passed a pubsub value.
  Since we don't work with the pubsub value directly in Reason we are defining it as an abstract type.
 */

let init = (pubsub: Pubsub.t) => {
  let store = Store.create(Reducer.reducer, State.initialState);
  let _unsubscribe =
    Store.subscribe(store, state =>
      Pubsub.publishState(pubsub, Subscription.mapToSchemaState(state))
    );

  {
    /* here we are passing the store as a dependency to the resolvers */
    "Query": Query.resolvers(store),
    "Mutation": Mutation.resolvers(store),
    "Subscription": Subscription.resolvers(pubsub),
  };
};