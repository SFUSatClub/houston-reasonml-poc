module MockedConnection =
  Connection.Make(
    {
      type t = string;
      let encode = s => Connection.Str(s);
    },
    {
      type t = string;
      let decode = Node_buffer.toString;
    },
  );

let init = (pubsub: Pubsub.t, port: Port.t) => {
  let link = MockedConnection.create(port);
  MockedConnection.listen(link);

  let con: Shared.con = {
    write: MockedConnection.write(link),
    subscribe: MockedConnection.subscribe(link),
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