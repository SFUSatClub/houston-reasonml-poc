# Houston

ReasonML + GraphQL + SerialPort proof of concept. You can read more about it here https://medium.com/sfu-sat/houston-reasonml-serialport-graphql-b3d6f1532a2

## Getting stated

- first [setup ReasonML](https://reasonml.github.io/docs/en/installation)
- then `npm install` and `npm start` and go to http://localhost:4000
- you can explore the `schema.graphql` to learn more about the functionalities available to you

## Create a command sequence

```graphql
mutation {
  createCommandSequence(
    sequence: {
      name: "sn"
      description: "sd"
      commands: [{ name: "cn", timeout: 14000, wait: 4000, arguments: [] }]
    }
  ) {
    id
  }
}
```

## Listen for state changes

In a new tab

```graphql
subscription {
  state {
    uplink {
      inProgress
      sequenceId
      pending
      unresolved
      successful
      failed
    }
  }
}
```

## Execute the command sequence

In a new tab

```graphql
mutation {
  uplinkCommandSequence(id: "fd9220efed406a1a0324398e8e44d71a44b65d11")
}
```
