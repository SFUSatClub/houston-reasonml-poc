# Port

- `Port` A wrapper around SerialPort port for interoperability.
- `Connection` We won't directly write to a Port. We use connection for this.
  To create a connection module, you need to specify a Encoder and Decoder. For example

```reason
module MockEncoder = {
  type t = string;
  let encode = s => Str(s);
};

module MockDecoder = {
  type t = string;
  let decode = Node_buffer.toString;
};

module Con = Make(MockEncoder, MockDecoder);
```

## A connection module exposes

- `create` creates a connection for a given port
- `write` call write to write to the port
- `subscribe` You can subscribe to the port data by calling subscribe and passing a callback
- `listen` Call listen to start watching the port of data
