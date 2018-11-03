# src

## Structure

- `command_sequence` where we store the serialized command sequence
- `resolvers` hold the implementation for the Mutation, Query and Subscription resolvers to satisfy the GraphQL Schema
- `store` manages the state of the application
- `uplink` uplink the a command sequence
- `index.js` initializes the GraphQLServer
- `schema.graphql` the schema we use to communicate with the client
