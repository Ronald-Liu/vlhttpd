var editor;
$(document).ready(function(){

$("#update").click(function()
{
	$.post("/cgi-bin/changeConfig.py", {"newConfig":editor.get()});
});

$("#restart").click(function(){
	$.post("/cgi-bin/changeConfig.py",{"restart":true});
});
	editor = new jsoneditor.JSONEditor(document.getElementById('jEditor'));
	$.get("/cgi-bin/getConfig.py", {}, function(data){
		$(status).html("Configure loaded");
		editor.set(data);
	})
});
