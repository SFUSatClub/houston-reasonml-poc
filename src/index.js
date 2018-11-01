const { GraphQLServer, PubSub } = require("graphql-yoga");

const pubsub = new PubSub();
const resolvers = require("./resolvers/Resolvers.bs").resolvers;

const server = new GraphQLServer({
  typeDefs: "./src/schema.graphql",
  resolvers,
  context: { pubsub }
});

server.start(() => console.log(`Server is running on http://localhost:4000`));
