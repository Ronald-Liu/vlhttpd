#pragma once
#include <string>
#include <cctype>
#include <algorithm>

class X_utils{
public:
	static std::string surfix2mime(std::string surfix){
		//a null-string is returned if not matched
		if(surfix.empty())
			return "";
		if(surfix.at(0)!='.')
			surfix = '.'+surfix;

		if(surfix == ".323")
			return "text/h323";
		if(surfix == ".3gp")
			return "video/3gpp";
		if(surfix == ".aab")
			return "application/x-authoware-bin";
		if(surfix == ".aam")
			return "application/x-authoware-map";
		if(surfix == ".aas")
			return "application/x-authoware-seg";
		if(surfix == ".acx")
			return "application/internet-property-stream";
		if(surfix == ".ai")
			return "application/postscript";
		if(surfix == ".aif")
			return "audio/x-aiff";
		if(surfix == ".aifc")
			return "audio/x-aiff";
		if(surfix == ".aiff")
			return "audio/x-aiff";
		if(surfix == ".als")
			return "audio/X-Alpha5";
		if(surfix == ".amc")
			return "application/x-mpeg";
		if(surfix == ".ani")
			return "application/octet-stream";
		if(surfix == ".apk")
			return "application/vnd.android.package-archive";
		if(surfix == ".asc")
			return "text/plain";
		if(surfix == ".asd")
			return "application/astound";
		if(surfix == ".asf")
			return "video/x-ms-asf";
		if(surfix == ".asn")
			return "application/astound";
		if(surfix == ".asp")
			return "application/x-asap";
		if(surfix == ".asr")
			return "video/x-ms-asf";
		if(surfix == ".asx")
			return "video/x-ms-asf";
		if(surfix == ".au")
			return "audio/basic";
		if(surfix == ".avb")
			return "application/octet-stream";
		if(surfix == ".avi")
			return "video/x-msvideo";
		if(surfix == ".awb")
			return "audio/amr-wb";
		if(surfix == ".axs")
			return "application/olescript";
		if(surfix == ".bas")
			return "text/plain";
		if(surfix == ".bcpio")
			return "application/x-bcpio";
		if(surfix == ".bin ")
			return "application/octet-stream";
		if(surfix == ".bld")
			return "application/bld";
		if(surfix == ".bld2")
			return "application/bld2";
		if(surfix == ".bmp")
			return "image/bmp";
		if(surfix == ".bpk")
			return "application/octet-stream";
		if(surfix == ".bz2")
			return "application/x-bzip2";
		if(surfix == ".c")
			return "text/plain";
		if(surfix == ".cal")
			return "image/x-cals";
		if(surfix == ".cat")
			return "application/vnd.ms-pkiseccat";
		if(surfix == ".ccn")
			return "application/x-cnc";
		if(surfix == ".cco")
			return "application/x-cocoa";
		if(surfix == ".cdf")
			return "application/x-cdf";
		if(surfix == ".cer")
			return "application/x-x509-ca-cert";
		if(surfix == ".cgi")
			return "magnus-internal/cgi";
		if(surfix == ".chat")
			return "application/x-chat";
		if(surfix == ".class")
			return "application/octet-stream";
		if(surfix == ".clp")
			return "application/x-msclip";
		if(surfix == ".cmx")
			return "image/x-cmx";
		if(surfix == ".co")
			return "application/x-cult3d-object";
		if(surfix == ".cod")
			return "image/cis-cod";
		if(surfix == ".conf")
			return "text/plain";
		if(surfix == ".cpio")
			return "application/x-cpio";
		if(surfix == ".cpp")
			return "text/plain";
		if(surfix == ".cpt")
			return "application/mac-compactpro";
		if(surfix == ".crd")
			return "application/x-mscardfile";
		if(surfix == ".crl")
			return "application/pkix-crl";
		if(surfix == ".crt")
			return "application/x-x509-ca-cert";
		if(surfix == ".csh")
			return "application/x-csh";
		if(surfix == ".csm")
			return "chemical/x-csml";
		if(surfix == ".csml")
			return "chemical/x-csml";
		if(surfix == ".css")
			return "text/css";
		if(surfix == ".cur")
			return "application/octet-stream";
		if(surfix == ".dcm")
			return "x-lml/x-evm";
		if(surfix == ".dcr")
			return "application/x-director";
		if(surfix == ".dcx")
			return "image/x-dcx";
		if(surfix == ".der")
			return "application/x-x509-ca-cert";
		if(surfix == ".dhtml")
			return "text/html";
		if(surfix == ".dir")
			return "application/x-director";
		if(surfix == ".dll")
			return "application/x-msdownload";
		if(surfix == ".dmg")
			return "application/octet-stream";
		if(surfix == ".dms")
			return "application/octet-stream";
		if(surfix == ".doc")
			return "application/msword";
		if(surfix == ".docx")
			return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
		if(surfix == ".dot")
			return "application/msword";
		if(surfix == ".dvi")
			return "application/x-dvi";
		if(surfix == ".dwf")
			return "drawing/x-dwf";
		if(surfix == ".dwg")
			return "application/x-autocad";
		if(surfix == ".dxf")
			return "application/x-autocad";
		if(surfix == ".dxr")
			return "application/x-director";
		if(surfix == ".ebk")
			return "application/x-expandedbook";
		if(surfix == ".emb")
			return "chemical/x-embl-dl-nucleotide";
		if(surfix == ".embl")
			return "chemical/x-embl-dl-nucleotide";
		if(surfix == ".eps")
			return "application/postscript";
		if(surfix == ".epub")
			return "application/epub+zip";
		if(surfix == ".eri")
			return "image/x-eri";
		if(surfix == ".es")
			return "audio/echospeech";
		if(surfix == ".esl")
			return "audio/echospeech";
		if(surfix == ".etc")
			return "application/x-earthtime";
		if(surfix == ".etx")
			return "text/x-setext";
		if(surfix == ".evm")
			return "x-lml/x-evm";
		if(surfix == ".evy")
			return "application/envoy";
		if(surfix == ".exe")
			return "application/octet-stream";
		if(surfix == ".fh4")
			return "image/x-freehand";
		if(surfix == ".fh5")
			return "image/x-freehand";
		if(surfix == ".fhc")
			return "image/x-freehand";
		if(surfix == ".fif")
			return "application/fractals";
		if(surfix == ".flr")
			return "x-world/x-vrml";
		if(surfix == ".flv")
			return "flv-application/octet-stream";
		if(surfix == ".fm")
			return "application/x-maker";
		if(surfix == ".fpx")
			return "image/x-fpx";
		if(surfix == ".fvi")
			return "video/isivideo";
		if(surfix == ".gau")
			return "chemical/x-gaussian-input";
		if(surfix == ".gca")
			return "application/x-gca-compressed";
		if(surfix == ".gdb")
			return "x-lml/x-gdb";
		if(surfix == ".gif")
			return "image/gif";
		if(surfix == ".gps")
			return "application/x-gps";
		if(surfix == ".gtar")
			return "application/x-gtar";
		if(surfix == ".gz")
			return "application/x-gzip";
		if(surfix == ".h")
			return "text/plain";
		if(surfix == ".hdf")
			return "application/x-hdf";
		if(surfix == ".hdm")
			return "text/x-hdml";
		if(surfix == ".hdml")
			return "text/x-hdml";
		if(surfix == ".hlp")
			return "application/winhlp";
		if(surfix == ".hqx")
			return "application/mac-binhex40";
		if(surfix == ".hta")
			return "application/hta";
		if(surfix == ".htc")
			return "text/x-component";
		if(surfix == ".htm")
			return "text/html";
		if(surfix == ".html")
			return "text/html";
		if(surfix == ".hts")
			return "text/html";
		if(surfix == ".htt")
			return "text/webviewhtml";
		if(surfix == ".ice")
			return "x-conference/x-cooltalk";
		if(surfix == ".ico")
			return "image/x-icon";
		if(surfix == ".ief")
			return "image/ief";
		if(surfix == ".ifm")
			return "image/gif";
		if(surfix == ".ifs")
			return "image/ifs";
		if(surfix == ".iii")
			return "application/x-iphone";
		if(surfix == ".imy")
			return "audio/melody";
		if(surfix == ".ins")
			return "application/x-internet-signup";
		if(surfix == ".ips")
			return "application/x-ipscript";
		if(surfix == ".ipx")
			return "application/x-ipix";
		if(surfix == ".isp")
			return "application/x-internet-signup";
		if(surfix == ".it")
			return "audio/x-mod";
		if(surfix == ".itz")
			return "audio/x-mod";
		if(surfix == ".ivr")
			return "i-world/i-vrml";
		if(surfix == ".j2k")
			return "image/j2k";
		if(surfix == ".jad")
			return "text/vnd.sun.j2me.app-descriptor";
		if(surfix == ".jam")
			return "application/x-jam";
		if(surfix == ".jar")
			return "application/java-archive";
		if(surfix == ".java")
			return "text/plain";
		if(surfix == ".jfif")
			return "image/pipeg";
		if(surfix == ".jnlp")
			return "application/x-java-jnlp-file";
		if(surfix == ".jpe")
			return "image/jpeg";
		if(surfix == ".jpeg")
			return "image/jpeg";
		if(surfix == ".jpg")
			return "image/jpeg";
		if(surfix == ".jpz")
			return "image/jpeg";
		if(surfix == ".js")
			return "application/x-javascript";
		if(surfix == ".jwc")
			return "application/jwc";
		if(surfix == ".kjx")
			return "application/x-kjx";
		if(surfix == ".lak")
			return "x-lml/x-lak";
		if(surfix == ".latex")
			return "application/x-latex";
		if(surfix == ".lcc")
			return "application/fastman";
		if(surfix == ".lcl")
			return "application/x-digitalloca";
		if(surfix == ".lcr")
			return "application/x-digitalloca";
		if(surfix == ".lgh")
			return "application/lgh";
		if(surfix == ".lha")
			return "application/octet-stream";
		if(surfix == ".lml")
			return "x-lml/x-lml";
		if(surfix == ".lmlpack")
			return "x-lml/x-lmlpack";
		if(surfix == ".log")
			return "text/plain";
		if(surfix == ".lsf")
			return "video/x-la-asf";
		if(surfix == ".lsx")
			return "video/x-la-asf";
		if(surfix == ".lzh")
			return "application/octet-stream";
		if(surfix == ".m13")
			return "application/x-msmediaview";
		if(surfix == ".m14")
			return "application/x-msmediaview";
		if(surfix == ".m15")
			return "audio/x-mod";
		if(surfix == ".m3u")
			return "audio/x-mpegurl";
		if(surfix == ".m3url")
			return "audio/x-mpegurl";
		if(surfix == ".m4a")
			return "audio/mp4a-latm";
		if(surfix == ".m4b")
			return "audio/mp4a-latm";
		if(surfix == ".m4p")
			return "audio/mp4a-latm";
		if(surfix == ".m4u")
			return "video/vnd.mpegurl";
		if(surfix == ".m4v")
			return "video/x-m4v";
		if(surfix == ".ma1")
			return "audio/ma1";
		if(surfix == ".ma2")
			return "audio/ma2";
		if(surfix == ".ma3")
			return "audio/ma3";
		if(surfix == ".ma5")
			return "audio/ma5";
		if(surfix == ".man")
			return "application/x-troff-man";
		if(surfix == ".map")
			return "magnus-internal/imagemap";
		if(surfix == ".mbd")
			return "application/mbedlet";
		if(surfix == ".mct")
			return "application/x-mascot";
		if(surfix == ".mdb")
			return "application/x-msaccess";
		if(surfix == ".mdz")
			return "audio/x-mod";
		if(surfix == ".me")
			return "application/x-troff-me";
		if(surfix == ".mel")
			return "text/x-vmel";
		if(surfix == ".mht")
			return "message/rfc822";
		if(surfix == ".mhtml")
			return "message/rfc822";
		if(surfix == ".mi")
			return "application/x-mif";
		if(surfix == ".mid")
			return "audio/mid";
		if(surfix == ".midi")
			return "audio/midi";
		if(surfix == ".mif")
			return "application/x-mif";
		if(surfix == ".mil")
			return "image/x-cals";
		if(surfix == ".mio")
			return "audio/x-mio";
		if(surfix == ".mmf")
			return "application/x-skt-lbs";
		if(surfix == ".mng")
			return "video/x-mng";
		if(surfix == ".mny")
			return "application/x-msmoney";
		if(surfix == ".moc")
			return "application/x-mocha";
		if(surfix == ".mocha")
			return "application/x-mocha";
		if(surfix == ".mod")
			return "audio/x-mod";
		if(surfix == ".mof")
			return "application/x-yumekara";
		if(surfix == ".mol")
			return "chemical/x-mdl-molfile";
		if(surfix == ".mop")
			return "chemical/x-mopac-input";
		if(surfix == ".mov")
			return "video/quicktime";
		if(surfix == ".movie")
			return "video/x-sgi-movie";
		if(surfix == ".mp2")
			return "video/mpeg";
		if(surfix == ".mp3")
			return "audio/mpeg";
		if(surfix == ".mp4")
			return "video/mp4";
		if(surfix == ".mpa")
			return "video/mpeg";
		if(surfix == ".mpc")
			return "application/vnd.mpohun.certificate";
		if(surfix == ".mpe")
			return "video/mpeg";
		if(surfix == ".mpeg")
			return "video/mpeg";
		if(surfix == ".mpg")
			return "video/mpeg";
		if(surfix == ".mpg4")
			return "video/mp4";
		if(surfix == ".mpga")
			return "audio/mpeg";
		if(surfix == ".mpn")
			return "application/vnd.mophun.application";
		if(surfix == ".mpp")
			return "application/vnd.ms-project";
		if(surfix == ".mps")
			return "application/x-mapserver";
		if(surfix == ".mpv2")
			return "video/mpeg";
		if(surfix == ".mrl")
			return "text/x-mrml";
		if(surfix == ".mrm")
			return "application/x-mrm";
		if(surfix == ".ms")
			return "application/x-troff-ms";
		if(surfix == ".msg")
			return "application/vnd.ms-outlook";
		if(surfix == ".mts")
			return "application/metastream";
		if(surfix == ".mtx")
			return "application/metastream";
		if(surfix == ".mtz")
			return "application/metastream";
		if(surfix == ".mvb")
			return "application/x-msmediaview";
		if(surfix == ".mzv")
			return "application/metastream";
		if(surfix == ".nar")
			return "application/zip";
		if(surfix == ".nbmp")
			return "image/nbmp";
		if(surfix == ".nc")
			return "application/x-netcdf";
		if(surfix == ".ndb")
			return "x-lml/x-ndb";
		if(surfix == ".ndwn")
			return "application/ndwn";
		if(surfix == ".nif")
			return "application/x-nif";
		if(surfix == ".nmz")
			return "application/x-scream";
		if(surfix == ".nokia-op-logo")
			return "image/vnd.nok-oplogo-color";
		if(surfix == ".npx")
			return "application/x-netfpx";
		if(surfix == ".nsnd")
			return "audio/nsnd";
		if(surfix == ".nva")
			return "application/x-neva1";
		if(surfix == ".nws")
			return "message/rfc822";
		if(surfix == ".oda")
			return "application/oda";
		if(surfix == ".ogg")
			return "audio/ogg";
		if(surfix == ".oom")
			return "application/x-AtlasMate-Plugin";
		if(surfix == ".p10")
			return "application/pkcs10";
		if(surfix == ".p12")
			return "application/x-pkcs12";
		if(surfix == ".p7b")
			return "application/x-pkcs7-certificates";
		if(surfix == ".p7c")
			return "application/x-pkcs7-mime";
		if(surfix == ".p7m")
			return "application/x-pkcs7-mime";
		if(surfix == ".p7r")
			return "application/x-pkcs7-certreqresp";
		if(surfix == ".p7s")
			return "application/x-pkcs7-signature";
		if(surfix == ".pac")
			return "audio/x-pac";
		if(surfix == ".pae")
			return "audio/x-epac";
		if(surfix == ".pan")
			return "application/x-pan";
		if(surfix == ".pbm")
			return "image/x-portable-bitmap";
		if(surfix == ".pcx")
			return "image/x-pcx";
		if(surfix == ".pda")
			return "image/x-pda";
		if(surfix == ".pdb")
			return "chemical/x-pdb";
		if(surfix == ".pdf")
			return "application/pdf";
		if(surfix == ".pfr")
			return "application/font-tdpfr";
		if(surfix == ".pfx")
			return "application/x-pkcs12";
		if(surfix == ".pgm")
			return "image/x-portable-graymap";
		if(surfix == ".pict")
			return "image/x-pict";
		if(surfix == ".pko")
			return "application/ynd.ms-pkipko";
		if(surfix == ".pm")
			return "application/x-perl";
		if(surfix == ".pma")
			return "application/x-perfmon";
		if(surfix == ".pmc")
			return "application/x-perfmon";
		if(surfix == ".pmd")
			return "application/x-pmd";
		if(surfix == ".pml")
			return "application/x-perfmon";
		if(surfix == ".pmr")
			return "application/x-perfmon";
		if(surfix == ".pmw")
			return "application/x-perfmon";
		if(surfix == ".png")
			return "image/png";
		if(surfix == ".pnm")
			return "image/x-portable-anymap";
		if(surfix == ".pnz")
			return "image/png";
		if(surfix == ".pot,")
			return "application/vnd.ms-powerpoint";
		if(surfix == ".ppm")
			return "image/x-portable-pixmap";
		if(surfix == ".pps")
			return "application/vnd.ms-powerpoint";
		if(surfix == ".ppt")
			return "application/vnd.ms-powerpoint";
		if(surfix == ".pptx")
			return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		if(surfix == ".pqf")
			return "application/x-cprplayer";
		if(surfix == ".pqi")
			return "application/cprplayer";
		if(surfix == ".prc")
			return "application/x-prc";
		if(surfix == ".prf")
			return "application/pics-rules";
		if(surfix == ".prop")
			return "text/plain";
		if(surfix == ".proxy")
			return "application/x-ns-proxy-autoconfig";
		if(surfix == ".ps")
			return "application/postscript";
		if(surfix == ".ptlk")
			return "application/listenup";
		if(surfix == ".pub")
			return "application/x-mspublisher";
		if(surfix == ".pvx")
			return "video/x-pv-pvx";
		if(surfix == ".qcp")
			return "audio/vnd.qcelp";
		if(surfix == ".qt")
			return "video/quicktime";
		if(surfix == ".qti")
			return "image/x-quicktime";
		if(surfix == ".qtif")
			return "image/x-quicktime";
		if(surfix == ".r3t")
			return "text/vnd.rn-realtext3d";
		if(surfix == ".ra")
			return "audio/x-pn-realaudio";
		if(surfix == ".ram")
			return "audio/x-pn-realaudio";
		if(surfix == ".rar")
			return "application/octet-stream";
		if(surfix == ".ras")
			return "image/x-cmu-raster";
		if(surfix == ".rc")
			return "text/plain";
		if(surfix == ".rdf")
			return "application/rdf+xml";
		if(surfix == ".rf")
			return "image/vnd.rn-realflash";
		if(surfix == ".rgb")
			return "image/x-rgb";
		if(surfix == ".rlf")
			return "application/x-richlink";
		if(surfix == ".rm")
			return "audio/x-pn-realaudio";
		if(surfix == ".rmf")
			return "audio/x-rmf";
		if(surfix == ".rmi")
			return "audio/mid";
		if(surfix == ".rmm")
			return "audio/x-pn-realaudio";
		if(surfix == ".rmvb")
			return "audio/x-pn-realaudio";
		if(surfix == ".rnx")
			return "application/vnd.rn-realplayer";
		if(surfix == ".roff")
			return "application/x-troff";
		if(surfix == ".rp")
			return "image/vnd.rn-realpix";
		if(surfix == ".rpm")
			return "audio/x-pn-realaudio-plugin";
		if(surfix == ".rt")
			return "text/vnd.rn-realtext";
		if(surfix == ".rte")
			return "x-lml/x-gps";
		if(surfix == ".rtf")
			return "application/rtf";
		if(surfix == ".rtg")
			return "application/metastream";
		if(surfix == ".rtx")
			return "text/richtext";
		if(surfix == ".rv")
			return "video/vnd.rn-realvideo";
		if(surfix == ".rwc")
			return "application/x-rogerwilco";
		if(surfix == ".s3m")
			return "audio/x-mod";
		if(surfix == ".s3z")
			return "audio/x-mod";
		if(surfix == ".sca")
			return "application/x-supercard";
		if(surfix == ".scd")
			return "application/x-msschedule";
		if(surfix == ".sct")
			return "text/scriptlet";
		if(surfix == ".sdf")
			return "application/e-score";
		if(surfix == ".sea")
			return "application/x-stuffit";
		if(surfix == ".setpay")
			return "application/set-payment-initiation";
		if(surfix == ".setreg")
			return "application/set-registration-initiation";
		if(surfix == ".sgm")
			return "text/x-sgml";
		if(surfix == ".sgml")
			return "text/x-sgml";
		if(surfix == ".sh")
			return "application/x-sh";
		if(surfix == ".shar")
			return "application/x-shar";
		if(surfix == ".shtml")
			return "magnus-internal/parsed-html";
		if(surfix == ".shw")
			return "application/presentations";
		if(surfix == ".si6")
			return "image/si6";
		if(surfix == ".si7")
			return "image/vnd.stiwap.sis";
		if(surfix == ".si9")
			return "image/vnd.lgtwap.sis";
		if(surfix == ".sis")
			return "application/vnd.symbian.install";
		if(surfix == ".sit")
			return "application/x-stuffit";
		if(surfix == ".skd")
			return "application/x-Koan";
		if(surfix == ".skm")
			return "application/x-Koan";
		if(surfix == ".skp")
			return "application/x-Koan";
		if(surfix == ".skt")
			return "application/x-Koan";
		if(surfix == ".slc")
			return "application/x-salsa";
		if(surfix == ".smd")
			return "audio/x-smd";
		if(surfix == ".smi")
			return "application/smil";
		if(surfix == ".smil")
			return "application/smil";
		if(surfix == ".smp")
			return "application/studiom";
		if(surfix == ".smz")
			return "audio/x-smd";
		if(surfix == ".snd")
			return "audio/basic";
		if(surfix == ".spc")
			return "application/x-pkcs7-certificates";
		if(surfix == ".spl")
			return "application/futuresplash";
		if(surfix == ".spr")
			return "application/x-sprite";
		if(surfix == ".sprite")
			return "application/x-sprite";
		if(surfix == ".sdp")
			return "application/sdp";
		if(surfix == ".spt")
			return "application/x-spt";
		if(surfix == ".src")
			return "application/x-wais-source";
		if(surfix == ".sst")
			return "application/vnd.ms-pkicertstore";
		if(surfix == ".stk")
			return "application/hyperstudio";
		if(surfix == ".stl")
			return "application/vnd.ms-pkistl";
		if(surfix == ".stm")
			return "text/html";
		if(surfix == ".svg")
			return "image/svg+xml";
		if(surfix == ".sv4cpio")
			return "application/x-sv4cpio";
		if(surfix == ".sv4crc")
			return "application/x-sv4crc";
		if(surfix == ".svf")
			return "image/vnd";
		if(surfix == ".svg")
			return "image/svg+xml";
		if(surfix == ".svh")
			return "image/svh";
		if(surfix == ".svr")
			return "x-world/x-svr";
		if(surfix == ".swf")
			return "application/x-shockwave-flash";
		if(surfix == ".swfl")
			return "application/x-shockwave-flash";
		if(surfix == ".t")
			return "application/x-troff";
		if(surfix == ".tad")
			return "application/octet-stream";
		if(surfix == ".talk")
			return "text/x-speech";
		if(surfix == ".tar")
			return "application/x-tar";
		if(surfix == ".taz")
			return "application/x-tar";
		if(surfix == ".tbp")
			return "application/x-timbuktu";
		if(surfix == ".tbt")
			return "application/x-timbuktu";
		if(surfix == ".tcl")
			return "application/x-tcl";
		if(surfix == ".tex")
			return "application/x-tex";
		if(surfix == ".texi")
			return "application/x-texinfo";
		if(surfix == ".texinfo")
			return "application/x-texinfo";
		if(surfix == ".tgz")
			return "application/x-compressed";
		if(surfix == ".thm")
			return "application/vnd.eri.thm";
		if(surfix == ".tif")
			return "image/tiff";
		if(surfix == ".tiff")
			return "image/tiff";
		if(surfix == ".tki")
			return "application/x-tkined";
		if(surfix == ".tkined")
			return "application/x-tkined";
		if(surfix == ".toc")
			return "application/toc";
		if(surfix == ".toy")
			return "image/toy";
		if(surfix == ".tr")
			return "application/x-troff";
		if(surfix == ".trk")
			return "x-lml/x-gps";
		if(surfix == ".trm")
			return "application/x-msterminal";
		if(surfix == ".tsi")
			return "audio/tsplayer";
		if(surfix == ".tsp")
			return "application/dsptype";
		if(surfix == ".tsv")
			return "text/tab-separated-values";
		if(surfix == ".ttf")
			return "application/octet-stream";
		if(surfix == ".ttz")
			return "application/t-time";
		if(surfix == ".txt")
			return "text/plain";
		if(surfix == ".uls")
			return "text/iuls";
		if(surfix == ".ult")
			return "audio/x-mod";
		if(surfix == ".ustar")
			return "application/x-ustar";
		if(surfix == ".uu")
			return "application/x-uuencode";
		if(surfix == ".uue")
			return "application/x-uuencode";
		if(surfix == ".vcd")
			return "application/x-cdlink";
		if(surfix == ".vcf")
			return "text/x-vcard";
		if(surfix == ".vdo")
			return "video/vdo";
		if(surfix == ".vib")
			return "audio/vib";
		if(surfix == ".viv")
			return "video/vivo";
		if(surfix == ".vivo")
			return "video/vivo";
		if(surfix == ".vmd")
			return "application/vocaltec-media-desc";
		if(surfix == ".vmf")
			return "application/vocaltec-media-file";
		if(surfix == ".vmi")
			return "application/x-dreamcast-vms-info";
		if(surfix == ".vms")
			return "application/x-dreamcast-vms";
		if(surfix == ".vox")
			return "audio/voxware";
		if(surfix == ".vqe")
			return "audio/x-twinvq-plugin";
		if(surfix == ".vqf")
			return "audio/x-twinvq";
		if(surfix == ".vql")
			return "audio/x-twinvq";
		if(surfix == ".vre")
			return "x-world/x-vream";
		if(surfix == ".vrml")
			return "x-world/x-vrml";
		if(surfix == ".vrt")
			return "x-world/x-vrt";
		if(surfix == ".vrw")
			return "x-world/x-vream";
		if(surfix == ".vts")
			return "workbook/formulaone";
		if(surfix == ".wav")
			return "audio/x-wav";
		if(surfix == ".wax")
			return "audio/x-ms-wax";
		if(surfix == ".wbmp")
			return "image/vnd.wap.wbmp";
		if(surfix == ".wcm")
			return "application/vnd.ms-works";
		if(surfix == ".wdb")
			return "application/vnd.ms-works";
		if(surfix == ".web")
			return "application/vnd.xara";
		if(surfix == ".wi")
			return "image/wavelet";
		if(surfix == ".wis")
			return "application/x-InstallShield";
		if(surfix == ".wks")
			return "application/vnd.ms-works";
		if(surfix == ".wm")
			return "video/x-ms-wm";
		if(surfix == ".wma")
			return "audio/x-ms-wma";
		if(surfix == ".wmd")
			return "application/x-ms-wmd";
		if(surfix == ".wmf")
			return "application/x-msmetafile";
		if(surfix == ".wml")
			return "text/vnd.wap.wml";
		if(surfix == ".wmlc")
			return "application/vnd.wap.wmlc";
		if(surfix == ".wmls")
			return "text/vnd.wap.wmlscript";
		if(surfix == ".wmlsc")
			return "application/vnd.wap.wmlscriptc";
		if(surfix == ".wmlscript")
			return "text/vnd.wap.wmlscript";
		if(surfix == ".wmv")
			return "audio/x-ms-wmv";
		if(surfix == ".wmx")
			return "video/x-ms-wmx";
		if(surfix == ".wmz")
			return "application/x-ms-wmz";
		if(surfix == ".wpng")
			return "image/x-up-wpng";
		if(surfix == ".wps")
			return "application/vnd.ms-works";
		if(surfix == ".wpt")
			return "x-lml/x-gps";
		if(surfix == ".wri")
			return "application/x-mswrite";
		if(surfix == ".wrl")
			return "x-world/x-vrml";
		if(surfix == ".wrz")
			return "x-world/x-vrml";
		if(surfix == ".ws")
			return "text/vnd.wap.wmlscript";
		if(surfix == ".wsc")
			return "application/vnd.wap.wmlscriptc";
		if(surfix == ".wv")
			return "video/wavelet";
		if(surfix == ".wvx")
			return "video/x-ms-wvx";
		if(surfix == ".wxl")
			return "application/x-wxl";
		if(surfix == ".x-gzip")
			return "application/x-gzip";
		if(surfix == ".xaf")
			return "x-world/x-vrml";
		if(surfix == ".xar")
			return "application/vnd.xara";
		if(surfix == ".xbm")
			return "image/x-xbitmap";
		if(surfix == ".xdm")
			return "application/x-xdma";
		if(surfix == ".xdma")
			return "application/x-xdma";
		if(surfix == ".xdw")
			return "application/vnd.fujixerox.docuworks";
		if(surfix == ".xht")
			return "application/xhtml+xml";
		if(surfix == ".xhtm")
			return "application/xhtml+xml";
		if(surfix == ".xhtml")
			return "application/xhtml+xml";
		if(surfix == ".xla")
			return "application/vnd.ms-excel";
		if(surfix == ".xlc")
			return "application/vnd.ms-excel";
		if(surfix == ".xll")
			return "application/x-excel";
		if(surfix == ".xlm")
			return "application/vnd.ms-excel";
		if(surfix == ".xls")
			return "application/vnd.ms-excel";
		if(surfix == ".xlsx")
			return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		if(surfix == ".xlt")
			return "application/vnd.ms-excel";
		if(surfix == ".xlw")
			return "application/vnd.ms-excel";
		if(surfix == ".xm")
			return "audio/x-mod";
		if(surfix == ".xml")
			return "text/plain";
		if(surfix == ".xmz")
			return "audio/x-mod";
		if(surfix == ".xof")
			return "x-world/x-vrml";
		if(surfix == ".xpi")
			return "application/x-xpinstall";
		if(surfix == ".xpm")
			return "image/x-xpixmap";
		if(surfix == ".xsit")
			return "text/xml";
		if(surfix == ".xsl")
			return "text/xml";
		if(surfix == ".xul")
			return "text/xul";
		if(surfix == ".xwd")
			return "image/x-xwindowdump";
		if(surfix == ".xyz")
			return "chemical/x-pdb";
		if(surfix == ".yz1")
			return "application/x-yz1";
		if(surfix == ".z")
			return "application/x-compress";
		if(surfix == ".zac")
			return "application/x-zaurus-zac";
		if(surfix == ".zip")
			return "application/zip";
		if(surfix == ".json")
			return "application/json";
		
		return "";
	}
	static std::string name2mime(std::string name){
		//a null-string is returned if not matched
		int lastDot = name.find_last_of('.');
		if (lastDot <= 0)
			return "";
		return surfix2mime(name.substr(lastDot,(name.length())-1));
	}
};

