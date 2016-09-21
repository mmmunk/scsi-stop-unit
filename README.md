# scsi-stop-unit
Small Linux utility to spin down a harddisk immediately.

## Usage
`scsi-stop-unit` *device*

### Example
`scsi-stop-unit /dev/sda`

You must have superuser (root) privilege to run this utility. Use for example in an automated job to spin down a server harddisk every night. The harddisk will automatically spin up at next use.
