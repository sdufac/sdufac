<?php

session_start();

if(!isset($_SESSION['panier_qte']) && !isset($_SESSION['panier_ref']))
{
    $_SESSION['panier_qte']= array();
    $_SESSION['panier_ref']= array();
}


$html = <<<HTML

<html>
<head>
<title>menu</title>
<link href="style.css" rel="stylesheet" type="text/css">
</head>
<body>
<p class="centre">
<h2>Sté Lafleur</h2>
<a href="logo.htm" target="page">Accueil</a>
</p>
<hr/>

<u><b>Nos produits</b></u>
HTML;

try
{
    $pdo= new PDO("mysql:host=localhost;dbname=lafleur","root","");
    $pdocat = $pdo->query("SELECT * FROM categorie");

    foreach($pdocat as $row)
    {
        $html.='<p /><a href="pageproduit.php?catcode='.$row['cat_code'].'" target="page">'.$row['cat_libelle'].'</a>';    
    }
}
catch(Exeption $e)
{
    echo "<p>ERREUR : ".$e->getMessage();
}

$html.='<center><hr><a href="videpanier.php" target="page"><button type="button">Vider le panier</button></a></center><br>
        <center><a href="panier.php" target="page"><button type="button">Commander</button></a><br></center>
        <br><center><a href="mailto:commercial@lafleur.com">Nous contacter</a></center>';


echo $html.="</body></html>";
