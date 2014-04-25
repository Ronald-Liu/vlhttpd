import cgi
import os,time

import config
form = cgi.FieldStorage()

if (form.has_key('newConfig')):
	fout = open(config.configPath,'w')
	fout.write(form['newConfig'].value)
	fout.close()

if (form.has_key('restart')):
	os.system("start cmd /K %s %s" %(config.restartBat,config.exePath))
