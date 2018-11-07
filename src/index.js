/**
 * SerialPort
 */
const SerialPort = require("@serialport/stream");
const Readline = require("@serialport/parser-readline");
const MockBinding = require("@serialport/binding-mock");

SerialPort.Binding = MockBinding;

MockBinding.createPort("/dev/ROBOT", { echo: true, record: true });
const port = new SerialPort("/dev/ROBOT");
port.pipe(new Readline({ delimiter: "\n" }));

/**
 * GraphQL
 */
const { GraphQLServer, PubSub } = require("graphql-yoga");

const pubsub = new PubSub();
const resolvers = require("./resolvers/Resolvers.bs").init(pubsub, port);

const server = new GraphQLServer({
  typeDefs: "./src/schema.graphql",
  resolvers,
  context: { pubsub }
});

server.start(() => console.log(`Server is running on http://localhost:4000`));
