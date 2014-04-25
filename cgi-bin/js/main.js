var editor;
$(document).ready(function(){

$("#update").click(function()
{
	$.post("changeConfig.py", {"newConfig":JSON.stringify(editor.get())});
});

$("#restart").click(function(){
	$.post("changeConfig.py",{"restart":true});
});
	editor = new jsoneditor.JSONEditor(document.getElementById('jEditor'));
	$.get("getConfig.py", function(data){
		$("#status").html("Configure loaded");
		editor.set(data);
	});
});
