window.onunload = backAlert();
   function backAlert()
   {
      window.onbeforeunload = function ()
      {
         if (true)
         {
            //alert( "Warning! If you go back, your data will not be saved.");
         }
      }
      return false;
   }
//This file contains all the basic javascript functions laoded along with every page in Licesing Client
var div_update,effect_update;
function page_laod()
 {
    
   if(readCookie("postback") == "false")
      {
      Effect.Grow('container',{direction:'top-left'});
      setCookie("up","1");      
      }
   else
	  updateui();  
 } 
 
 function readCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}

function setCookie(cookieName,cookieValue) {

 document.cookie = cookieName+"="+escape(cookieValue)+ ";";
}


function updateui() 
        {
    var ui_update= readCookie("updateui");    
	var ui = ui_update.split('#');

		div_update = ui[0];
	    effect_update = ui[1];
		
		if(div_update!="none")
		{
		   
			switch(effect_update)
				{
					case "blindup":	
					    {
					         if(readCookie("up")=="1")
					    	   {
					    	      Effect.BlindUp(div_update);					    	      		    	      
					    	      setCookie("up","0");
					    	      setCookie("down","1");
					   			}
					   		   else
					   		    $(div_update).style.display ="none";		    
					    break;
					    }
					case "blinddown":
					    {
					    if(readCookie("down")=="1")
					    	   {
					                 Effect.BlindDown(div_update);
					                 setCookie("up","1");
					                 setCookie("down","0");
					            }
					            else
					             $(div_update).style.display ="inline"
					   break;
					   }
				}
		}
	
     }
     
function popHiddenLayer() 
{
if(document.getElementById('hiddenLayer')!=null) 
{
var elem = document.getElementById('hiddenLayer');
elem.className = 'POP_LAYER';
}
return true;
} 
   
function setNewToDate(input)
{
    var validformat=/^\d{1,2}\/\d{1,2}\/\d{4}$/ //Basic check for format validity
    if (validformat.test(input.value)) 
    {
     //Detailed check for valid date ranges
        var monthfield = input.value.split("/")[0]
        var dayfield = input.value.split("/")[1]
        var yearfield = input.value.split("/")[2]
        var dayobj = new Date(yearfield, monthfield - 1, dayfield)
        if ((dayobj.getMonth() + 1 != monthfield) || (dayobj.getDate() != dayfield) || (dayobj.getFullYear() != yearfield)) {
            alert("Invalid Day, Month, or Year range detected. Please correct and submit again.");
            var today = new Date();
            document.getElementById('startdate_pick').value = today.getMonth() + 1 + "/" + today.getDate() + "/" + today.getFullYear();
            today.setDate(today.getDate() + 14);
            document.getElementById('todate_pick').value = today.getMonth() + 1 + "/" + today.getDate() + "/" + today.getFullYear();
        } else {
            var todate = new Date(dayobj.setDate(dayobj.getDate() + 14));
            document.getElementById('todate_pick').value = todate.getMonth() + 1 + "/" + todate.getDate() + "/" + todate.getFullYear();
        }
    }
}  
  
  
function isInteger(s)
{   var i;
    for (i = 0; i < s.length; i++)
    {   
        // Check that current character is number.
        var c = s.charAt(i);
        if ((c < "0") || (c > "9")) 
                return false;
    }
    // All characters are numbers.
    return true;
}

function isValidDate(s)
{   var i;
    for (i = 0; i < s.length; i++)
    {   
        // Check that current character is number.
        var c = s.charAt(i);
        if ((c < "0") || (c > "9")) 
        {
                alert("Enter Valid Date");
                return false;
        }
    }
    // All characters are numbers.
    return true;
}