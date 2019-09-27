/*
  © Copyright 2019 Nuovo, TD.
  Author Chatdanai Phakaket
  email nuovo.td@gmail.com
 */


const char Header_Page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Nuovo IoT Web Configure.</title>
<meta charset="utf-8">
</head>
<style>
input[type=text], input[type=password]{
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}

input[type=submit] {
  width: 100%;
  background-color: #4CAF50;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

input[type=submit]:hover {
  background-color: #45a049;
}

div {
  border-radius: 5px;
  background-color: #f2f2f2;
  padding: 20px;
}
</style>
<body>
<center>
<h2>Nuovo IoT Web Configure.</h2>
</center>
<div>
  <form action="http://192.168.10.1:8080/config" method="POST">
 )=====";   

const char Footer_Page[] PROGMEM = R"=====(
    <input type="submit" value="Submit">
  </form>
</div>
</body>
<script type="text/javascript">

xmlhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    var myArr = JSON.parse(this.responseText);
    document.getElementById("apName").value = myArr.APSSID;
    document.getElementById("apPasswd").value = myArr.APPasswd;
    document.getElementById("wifiName").value = myArr.WiFiSSID;
    document.getElementById("wifiPasswd").value = myArr.WiFiPasswd;
    document.getElementById("bToken").value = myArr.BToken;
  }
};
xmlhttp.open("GET", http://192.168.10.1:8080/getInitValue, true);
xmlhttp.send();


</script>
</html>
)=====";

