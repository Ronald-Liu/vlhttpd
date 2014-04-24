import cgi
form = cgi.FieldStorage()

import config
print "Content-Type:application/json\r\n\r\n"
fin = open(config.configPath,"r")
print fin.read()
fin.close()