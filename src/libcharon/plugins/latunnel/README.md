# latunnel Plugin

## Overview

The latunnel plugin is a strongSwan listener plugin that logs CHILD_SA events with specific tunnel information. It monitors CHILD_SA up, down, and rekey events and prints detailed information about the tunnel configuration.

## Features

- Monitors CHILD_SA up/down events
- Monitors CHILD_SA rekey events (logs both old and new SA information)
- Logs the following information for each event:
  - PLUTO_IF_ID_IN: Inbound interface ID
  - PLUTO_IF_ID_OUT: Outbound interface ID  
  - PLUTO_MY_SOURCEIP: Local virtual IP address
  - PLUTO_PEER_SOURCEIP: Peer virtual IP address
  - PLUTO_UNIQUEID: Unique IKE_SA identifier

## Configuration

To enable the latunnel plugin, add it to the strongSwan configuration:

```
charon {
    plugins {
        latunnel {
            load = yes
        }
    }
}
```

## Log Output

The plugin outputs logs at DBG_CHD level with the prefix "latunnel_listener:". Example output:

```
latunnel_listener: CHILD_SA UP event (current)
  PLUTO_IF_ID_IN=1
  PLUTO_IF_ID_OUT=2
  PLUTO_MY_SOURCEIP=10.0.0.1
  PLUTO_PEER_SOURCEIP=10.0.0.2
  PLUTO_UNIQUEID=12345

latunnel_listener: CHILD_SA REKEY event (old)
  PLUTO_IF_ID_IN=1
  PLUTO_IF_ID_OUT=2
  PLUTO_MY_SOURCEIP=10.0.0.1
  PLUTO_PEER_SOURCEIP=10.0.0.2
  PLUTO_UNIQUEID=12345

latunnel_listener: CHILD_SA REKEY event (new)
  PLUTO_IF_ID_IN=1
  PLUTO_IF_ID_OUT=2
  PLUTO_MY_SOURCEIP=10.0.0.1
  PLUTO_PEER_SOURCEIP=10.0.0.2
  PLUTO_UNIQUEID=12345
```

## Building

The plugin is built as part of the strongSwan build system. Make sure to include it in the plugin list during configuration.