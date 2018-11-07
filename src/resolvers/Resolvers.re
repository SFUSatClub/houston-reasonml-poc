let init = (pubsub: Pubsub.t, port: Port.t) => {
  let link = Connection.Con.create(port);
  Connection.Con.listen(link);

  let con: Shared.con = {
    write: Connection.Con.write(link),
    subscribe: Connection.Con.subscribe(link),
  };

  let store = Store.create(Reducer.reducer, State.initialState);
  let _unsubscribe =
    Store.subscribe(store, state =>
      Pubsub.publishState(pubsub, Subscription.mapToSchemaState(state))
    );

  let dep: Shared.dep = {store, con};

  {
    /* here we are passing the store as a dependency to the resolvers */
    "Query": Query.resolvers,
    "Mutation": Mutation.resolvers(dep),
    "Subscription": Subscription.resolvers(pubsub),
  };
};