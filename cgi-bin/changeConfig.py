import cgi

form = cgi.FieldStorage()

if (form.has_key('newConfig')):
	import config
	fout = open(config.configPath,'w')
	fout.write(form['newConfig'])
	fout.close()
if (form.has_key('restart')):
	import os,time
	os.system("taskkill /F /IM vlhttpd.exe")
	time.sleep(2)
	os.system("start cmd /k %s" %(config.exePath,))