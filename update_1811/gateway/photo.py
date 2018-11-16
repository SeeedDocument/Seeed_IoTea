#!/usr/bin/python

import boto3
import os
import time

# Create an S3 client
s3 = boto3.client('s3')
bucket_name = 'static.seeed.cc'

while True:
	try:
		localtime = time.localtime(time.time())
		if int(time.strftime('%M', localtime)) != 0:
			continue
		
		year = time.strftime('%Y', localtime)
		season = int(time.strftime('%m', localtime)) % 4 + 1
		filename = time.strftime('%Y%m%d-%H0000', localtime) + '.jpg'
		
		# Take photo
		os.system("fswebcam --no-banner -r 1920x1080 {}".format(filename))
		
		upload_path = 'files/iotea/{}s{}/{}'.format(year, season, filename)
		
		# Uploads the given file using a managed uploader, which will split up large
		# files automatically and upload parts in parallel.
		s3.upload_file(filename, bucket_name, upload_path)
		print('Uploaded file to {}'.format(upload_path))
		
		# Remove local file
		os.remove(filename)
		print('Deleted local file {}'.format(filename))
	except:
		continue
	finally:
		time.sleep(60)
