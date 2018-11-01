let store = Store.create(Reducer.reducer, State.initialState);

[@bs.val] [@bs.module "PubSub"] external publish : (string, 'a) => unit = "";

Store.subscribe(
  store,
  state => {
    let serializableState = State.stateToJs(state);
    publish("STATE", serializableState);
  },
);

type stateAsyncIterator;
[@bs.val] [@bs.module "./Subscription"]
external subscriptions : stateAsyncIterator = "";

let resolvers = {
  "Query": Query.resolvers(store),
  "Mutation": Mutation.resolvers(store),
  "Subscription": subscriptions,
};