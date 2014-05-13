// DOM element creator
function $new(tagName, attrs) {
    var e = document.createElement(tagName);
    if (attrs)
        for (attr in attrs)
            e.setAttribute(attr, attrs[attr]);
    return e;
}
// Selectors
function $id(id) {
    return document.getElementById(id);
}
function $class(className, element) {
    if (element)
        return element.getElementsByClassName(className);
    else
        return document.getElementsByClassName(className);
}
function $tag(tagName, element) {
    if (element)
        return element.getElementsByTagName(tagName);
    else
        return document.getElementsByTagName(tagName);
}
// Ajax methods
function $get(url, callback) {
    var ajax = new XMLHttpRequest();
    ajax.open("GET", url, true);
    ajax.onreadystatechange = function() {
        if (ajax.readyState == 4 && ajax.status == 200)
            callback(JSON.parse(ajax.responseText));
    };
    ajax.send();
}
function $post(url, argus, callback) {
    var ajax = new XMLHttpRequest();
    ajax.open("POST", url, true);
    ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    ajax.onreadystatechange = function() {
        if (ajax.readyState == 4 && ajax.status == 200)
            callback(JSON.parse(ajax.responseText));
    };
    var argusArray = [];
    for (arg in argus)
        argusArray.push(encodeURIComponent(arg) + "=" + encodeURIComponent(argus[arg]));
    ajax.send(argusArray.join("&"));
}
function $uploadFile(url, input, callback) {
    var ajax = new XMLHttpRequest();
    ajax.open("POST", url, true);
    var formData = new FormData();
    formData.append(input.name, input.files[0]);
    ajax.onreadystatechange = function() {
        if (ajax.readyState == 4 && ajax.status == 200)
            callback(JSON.parse(ajax.responseText));
    };
    ajax.send(formData);
}

// Other helpful functions

// Email checker
function isEmail(str){ 
    var reg = /^[a-z0-9]+([._\\-]*[a-z0-9])*@([a-z0-9]+[-a-z0-9]*[a-z0-9]+.){1,63}[a-z0-9]+$/; 
    return reg.test(str); 
} 
// Uploaded image previewer
function readURL(input, imgDOM) {
    if (input.files && input.files[0]) {
        var reader = new FileReader();
        reader.onload = function (e) {
            imgDOM.src = e.target.result;
        };
        reader.readAsDataURL(input.files[0]);
    }
}
