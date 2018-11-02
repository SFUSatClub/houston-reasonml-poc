# Resolvers

Implements Query, Mutation, and Subscription resolvers.

## Files

- `Query.re` Implements the Query root resolvers, `info` and `commandSequence`.
- `Mutation.re` Implements the Mutation root resolvers, `createCommandSequence` and `executeCommandSequence`
- `Subscription.js` Implments the Subscription root resolver `state`
- `Schema.re` Mirrors the object types in `schema.graphql` schema definition file
- `Resolver.re` Injects `state` into the Query and Mutation resolvers. Returns a resolver object that is passed to the `GraphQLServer` in the `index.js`

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
