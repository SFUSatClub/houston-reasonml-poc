const { GraphQLServer } = require("graphql-yoga");

const Query = require("./resolvers/Query.bs");
const Mutation = require("./resolvers/Mutation.bs");

const resolvers = {
  Query: Query.resolvers,
  Mutation: Mutation.resolvers
};

const server = new GraphQLServer({
  typeDefs: "./src/schema.graphql",
  resolvers
});

server.start(() => console.log(`Server is running on http://localhost:4000`));
