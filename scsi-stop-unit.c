/*
 * SCSI Stop Unit (scsi-stop-unit) Spin down harddisk
 * Version 0.9, 2016-09-21, Thomas Munk, mmmunk.dk
 * License: http://unlicense.org (Public Domain)
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <scsi/sg.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s device\n", argv[0]);
		return 1;
	}
	char *device = argv[1];
	printf("Stopping %s\n", device);

	int rc = 0;
	struct sg_io_hdr req;
	//unsigned char sense_buffer[200];
	int fd;

	/* Open device */
	fd = open(device, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 2;
	}

	/* SCSI Stop Unit IO request */
	memset(&req, 0, sizeof req);
	req.interface_id = 'S';
	req.dxfer_direction = SG_DXFER_NONE;
	req.cmdp = (unsigned char *)"\x1b\x00\x00\x00\x00\x00";
	req.cmd_len = 6;
	//req.sbp = sense_buffer;
	//req.mx_sb_len = sizeof sense_buffer;

	/* Execute request */
	if (ioctl(fd, SG_IO, &req) == -1) {
		perror("ioctl");
		rc = 3;
	}
	else
	if (req.masked_status != 0) {
		fprintf(stderr, "SCSI command failed (masked_status = 0x%02x)\n", req.masked_status);
		rc = 4;
	}

	/* Close and return */
	close(fd);
	return rc;
}
