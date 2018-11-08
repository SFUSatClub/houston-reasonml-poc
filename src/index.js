/**
 * SerialPort
 * Here we are setting up a Mocked port. We can write to this port and read back the echo (what we just wrote).
 * The
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
const resolvers = require("./resolvers/Resolvers.bs").init(pubsub, port); // Note that the resolvers take port and pubsub as dependencies.

const server = new GraphQLServer({
  typeDefs: "./src/schema.graphql",
  resolvers,
  context: { pubsub }
});

server.start(() => console.log(`Server is running on http://localhost:4000`));
