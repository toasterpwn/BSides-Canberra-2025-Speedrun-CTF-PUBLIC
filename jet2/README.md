# jet2

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| HexF | Finals     |   ItsIronicIInsist    | Gorg | Gorg |

<details>
  <summary>(SPOILER) Writeup</summary>

JSON is created through snprintf, which is will not escape any quotes put into a JSON string
```c
snprintf(body, sizeof(body), "{\"name\": \"%s %s %s\", \"cabin\": \"%s\", \"seat\": \"%s\"}",
        ticket->title, ticket->first_name, ticket->last_name,
        ticket->cabin,
        ticket->seat
        );
```
This allows us to add two duplicate keys to the JSON, of which the second will be kept by the verifying python server
</details>
