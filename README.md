# DNS Spoofing Daemon

This repository contains a minimal DNS spoofing daemon. For any A record
request it returns a hard-coded address value that the user can configure
from the command line.

## Architecture 

## Running and Testing
The workflow to demonstrate the functionality associated with this daemon matches the specifications in the assignment as such:
```
On localhost:
    # cd dns-spoof
    # make
    # make check
    # ./dnsspoof -p 123

Other terminal:
    # dig -p 123 @localhost foo.com

Other terminal:
    # dig -p 123 @localhost foo.com
```
This should return the following response:
TODO Modify if response approximates assignment more closely.
```
; <<>> DiG 9.16.1-Ubuntu <<>> -p 123 @localhost foo.com
; (1 server found)
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 46090
;; flags: aa rd; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0
;; WARNING: recursion requested but not available

;; QUESTION SECTION:
;foo.com.			IN	A

;; ANSWER SECTION:
foo.com.		60	IN	A	6.6.6.6

;; Query time: 0 msec
;; SERVER: 127.0.0.1#123(127.0.0.1)
;; WHEN: Wed Oct 28 02:16:08 EDT 2020
;; MSG SIZE  rcvd: 41
```
## Design Decisions
There are several major design decisions I thought through when working on this 
project.
One of the most important decisions I made involved how to process and manage
incoming packets. Upon reading the DNS specification, my first thought was to
create a struct where each field corresponded to a different value within the
DNS header. That way, I could simply deserialize and serialize incoming packets
as necessary. However, this quickly felt more high-overhead than expected in
the context of such a minimal implementation


## Resources
To develop this implementation, I extensively referenced and used the following
resources:

- [RFC 1035](https://tools.ietf.org/html/rfc1035): This was the version of the
  DNS spec I followed.
- [C Reference](https://devdocs.io/c/): I used this searchable reference when I
  wanted to understand or recall certain functions in C.
- [CUnit Documentation](http://cunit.sourceforge.net/doc/index.html): I looked
  at this resource to understand and implement unit testing.
- [DIG Command Documentation](https://www.hostinger.com/tutorials/how-to-use-the-dig-command-in-linux/#How-to-Use-the-Dig-Command): I used this resource to understand how to use the DIG comamnd.
- [Makefile Documentation](https://www.gnu.org/software/make/manual/make.html)

Any other specific references I used (i.e. stackoverflow links for specific commands) are linked in comments within the files.
