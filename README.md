# DNS Spoofing Daemon

This repository contains a minimal DNS spoofing daemon. For any A record
request it returns a hard-coded address value that the user can configure
from the command line.

## Architecture
This minimal implementation closely follows the DNS specification (RFC 1035) to
realize a DNS spoofing daemon capable of responding to simple quieries by
parsing incoming messages received over a specified socket. 


When initializing the program, the user can choose to provide values for the
port number on which the daemon operates and/or the hardcoded address the daemon
will automatically respond with as such:
```
sudo ./dnsspoof -a [DEFAULT_ADDRESS] -p [PORT_NUMBER]
```
From there, incoming queries on that port will receive a responses including that
default address.

## Running and Testing
The workflow to demonstrate the functionality associated with this daemon
matches the specifications in the assignment as such:
```
On localhost:
    # cd dns-spoof
    # make
    # make check
    # sudo ./dnsspoof -p 123

Other terminal:
    # dig -p 123 @localhost foo.com
```
This should return the following response in the other terminal.
```
; <<>> DiG 9.16.1-Ubuntu <<>> -p 123 @localhost foo.com
; (1 server found)
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 13928
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;foo.com.			IN	A

;; ANSWER SECTION:
foo.com.		3600	IN	A	6.6.6.6

;; Query time: 0 msec
;; SERVER: 127.0.0.1#123(127.0.0.1)
;; WHEN: Thu Oct 29 19:05:55 EDT 2020
;; MSG SIZE  rcvd: 41
```
## Design Decisions
There are several major design decisions I thought through when working on this 
project.
- One of the most important decisions I made involved how to process and manage
  incoming packets. Upon reading the DNS specification, my first thought was to
  create a struct where each field corresponded to a different value within the
  DNS header. That way, I could simply deserialize and serialize incoming
  packets as necessary. However, this quickly felt more high-overhead than
  expected in the context of such a minimal implementation: as all I needed
  to do wasmanipulate a few fields, I elected to just modify the message in
  place and then send it back. That being said, at a larger scale, a more
  tightly codified system that leverages frameworks such as structs would
  likely make sense. To make it easier to change the values of flags, I did
  some manual precomputation and stored values in the `dns_defns` header.
- I decided what functionality from within the DNS spec I ought to maintain and
  what functionality I could discard. I chose to prioritize including features
  that allowed me to realize the functionality associated with assigning the
  hardcoded address value to any input.

### Extensions
If I had additional time and resources to dedicate to this project, I would
extend this project in two major directions.

- Error Checking and Testing: The testing present here does not necessarily
  encapsulate all use cases and potential opportunities for user error.
  For example, none of the set methods validate if the input value for the
  parameter is appropriate for the application (beyond its datatype)

- Daemon Functionality: This daemon does not implement the entirety of the DNS
  specification, and further development could help approach that level of
  functionality.

## Resources
To develop this implementation, I extensively referenced and used the following
resources:

- [RFC 1035](https://tools.ietf.org/html/rfc1035): This was the version of the
  DNS spec I followed.
- [C Reference](https://devdocs.io/c/): I used this searchable reference when I
  wanted to understand or recall certain functions in C.
- [CUnit Documentation](http://cunit.sourceforge.net/doc/index.html): I looked
  at this resource to understand and implement unit testing.
- [DIG Command Documentation](https://www.hostinger.com/tutorials/how-to-use-the-dig-command-in-linux/#How-to-Use-the-Dig-Command): 
  I used this resource to understand how to use the DIG comamnd.
- [Makefile Documentation](https://www.gnu.org/software/make/manual/make.html)

I cite any other specific references I used (i.e. forum links for specific
commands) are linked in comments within the files.