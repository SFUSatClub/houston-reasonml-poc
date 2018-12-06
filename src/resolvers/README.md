# Resolvers

Implements Query, Mutation, and Subscription resolvers.

- You should read [Tutorial: GraphQL Subscriptions on the Server](https://blog.apollographql.com/tutorial-graphql-subscriptions-server-side-e51c32dc2951)
- You can read [Exploring Reason and GraphQL](https://blog.apollographql.com/exploring-reason-and-graphql-ff877df60d2a)

## Files

- `pubsub` A wrapper around GraphQL Pubsub for interoperability
- `Query.re` Implements the Query root resolvers, `info` and `commandSequence`.
- `Mutation.re` Implements the Mutation root resolvers, `createCommandSequence` and `executeCommandSequence`
- `Subscription.re` Implments the Subscription root resolver `state`
- `Schema.re` Mirrors the object types in `schema.graphql` schema definition file
- `Resolver.re` Injects `Shared.dep` into the Mutation resolvers and `pubsub` into the Subscription resolvers. Returns a resolver object that is passed to the `GraphQLServer` in the `index.js`

## Notes

### Inter operability

- If you see a code block like this in the `.re` files it for inter operability with JS.
  Here we are telling the Reason compiler that the function `readJsonFile` defined in the `./helpers` module is takes a string and returns a command sequence promise.

  ```reason
  [@bs.val] [@bs.module "./helpers"]
  external readJsonFile : string => Js.Promise.t(Schema.commandSequence) = "";
  ```

- We use ReasonML [Objects] to work with the input arguments to and the return values from the resolvers.

  ```reason
  type commandArgument = {
    .
    "id": string,
    "name": string,
    "value": string,
  };
  ```
