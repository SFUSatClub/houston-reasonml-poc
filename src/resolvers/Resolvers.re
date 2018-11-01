let store = Store.create(Reducer.reducer, State.initialState);

type stateAsyncIterator;
[@bs.val] [@bs.module "./Subscription"]
external subscriptions : stateAsyncIterator = "";

let resolvers = {
  "Query": Query.resolvers(store),
  "Mutation": Mutation.resolvers(store),
  "Subscription": subscriptions,
};