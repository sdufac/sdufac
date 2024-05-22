<?php

session_start();

$html = <<<HTML
<html>
<head>
<title>Bulbes</title>
</head>
<body bgcolor="#ffffff">
    <table  width="95%" border="1" cellspacing="0" cellpadding="4">
HTML;

try
{
    $pdo= new PDO("mysql:host=localhost;dbname=lafleur","root","");
    $pdoproduit = $pdo->query("SELECT * FROM produit WHERE pdt_categorie='".$_GET['catcode']."'");

    foreach($pdoproduit as $row)
    {
        $html.='<tr>
        <td align="center"><img src="images/'.$row['pdt_image'].'.jpg" /></td>
        <td>'.$row['pdt_ref'].'</td>
        <td>'.$row['pdt_designation'].'</td>
        <td align="right">'.$row['pdt_prix'].'€</td>
        </tr>';
    }

    $pdoproduit = $pdo->query("SELECT * FROM produit WHERE pdt_categorie='".$_GET['catcode']."'");


    $html.='

    <form action="panier.php?action=ajout" method="post">
        <table>
            <tr>
                <td><select name="produit">';
                foreach($pdoproduit as $ligne)
                {
                    $html.='<option value="'.$ligne['pdt_ref'].'">'.$ligne['pdt_designation'].'</option>';
                }
    $html.=     '</select>
                <td>Quantité <input type="text" name="quantite" size="3">
            </tr>
            <tr>
                <td><input type="submit" value="Ajouter">
            </tr>
        </table>
    </form>';

}
catch(Exeption $e)
{
    echo "<p>ERREUR : ".$e->getMessage();
}

echo $html.='</table></body></html>';
