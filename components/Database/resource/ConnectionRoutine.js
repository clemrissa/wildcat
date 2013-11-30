// Work around DatabaseType
// 
function convertToId(index) {
  return index + 2
}

function convertFromId(index) {
  return index - 2
}

var DatabaseTypeMap = {};
//DatabaseTypeMap[1] = "Unknown";
DatabaseTypeMap[2] = "MySQL";
DatabaseTypeMap[3] = "SQLite";

var DatabaseTypes = (function(e){var a=[];for (var i in e) a.push(e[i]); return a;})(DatabaseTypeMap)

// Work around statuses

function Status (text, image) {
    this.text = text;
    this.image = image;
}

var StatusMap = {};
StatusMap[1] = new Status("Disconnected", "imgs/arrow-circle-double-135-icon.png");
StatusMap[2] = new Status("Connected", "imgs/Circle-apply-icon.png");
StatusMap[3] = new Status("Failed", "imgs/open-file-icon.png");

function composeStatusMessage(status, error) {
  var message = StatusMap[status].text
    if (status == 3) {
      message += "with error: " + error;
    }
  return message
}
