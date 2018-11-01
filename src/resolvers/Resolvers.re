let store = Store.create(Reducer.reducer, State.initialState);

let resolvers = {
  "Query": Query.resolvers(store),
  "Mutation": Mutation.resolvers(store),
};