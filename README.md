# Getting stated

- first [setup ReasonML](https://reasonml.github.io/docs/en/installation)
- then `npm install` and `npm start` and go to http://localhost:4000

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
  state: {
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
  executeCommandSequence(id: "fd9220efed406a1a0324398e8e44d71a44b65d11")
}
```
