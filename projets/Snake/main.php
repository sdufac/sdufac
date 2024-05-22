<?php

$html = <<<HTML
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Snake</title>
</head>
<body>
    <table id="board">
HTML;

for($i=1;$i<11;$i++){
    $html.='<tr>';
    for($j=1;$j<11;$j++){
        $html.='<td id="'.$j.','.$i.'"></td>';
    }
    $html.='</tr>';
}

echo $html.='</table>
    <div id="score"></div>
    <script type="text/javascript" src="script.js"></script>
</body>
</html>';

//<input type="button" id="movel" value="left" onclick="move("left")">
//<input type="button" id="mover" value="right" onclick="move("right")">
//<input type="button" id="moveu" value="up" onclick="move("up")">
//<input type="button" id="moved" value="down" onclick="move("down")">