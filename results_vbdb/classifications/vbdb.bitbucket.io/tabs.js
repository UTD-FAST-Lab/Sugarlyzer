function tab(tabName, btn) {
    Array.from(document.getElementsByClassName("tab")).forEach(t => {
        t.style.backgroundColor = "inherit";
        
    });
    if(document.getElementById(tabName).style.display == "block")
    {
        document.getElementById(tabName).style.display = "none";
        return;
    }
    Array.from(document.getElementsByClassName("tabcontent")).forEach(t => {
        t.style.display = "none";
    })
    btn.style.backgroundColor = "lightgrey";
    document.getElementById(tabName).style.display = "block";
}