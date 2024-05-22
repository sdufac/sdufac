<?php

session_start();



$html = <<<HTML
<html>
<head>
<title>Bulbes</title>
</head>
<body>
    <h3>Votre panier :</h3>
    <table  width="95%" border="1" cellspacing="0" cellpadding="4">
        
HTML;

try
{
    $pdo= new PDO("mysql:host=localhost;dbname=lafleur","root","");

    $count=count($_SESSION['panier_ref']);
    
    //ajout dans le panier

    if(isset($_GET['action'])){
        if($_GET['action']=='ajout'){
            if(isset($_POST['quantite']) && isset($_POST['produit']))
            {
                $u=0;
                $trouve=false;
                foreach($_SESSION['panier_ref'] as $panierref)
                {
                    if($_POST['produit']==$panierref)
                    {
                        $_SESSION['panier_qte'][$u]=$_SESSION['panier_qte'][$u]+$_POST['quantite'];
                        $trouve=true;
                    }
                    $u++;                
                }
                
                if($trouve==false)
                {
                    $_SESSION['panier_qte'][$count]=$_POST['quantite'];
                    $_SESSION['panier_ref'][$count]=$_POST['produit'];
                }
            }
        }
    }

    //affichage du panier
    
    $count=count($_SESSION['panier_ref']);

    if(!empty($_SESSION['panier_qte']) && !empty($_SESSION['panier_ref']))
    {
        $html.="<tr><td><b>Ref</b><td><b>Designation</b><td><b>Px. Unit</b><td><b>Qté</b><td><b>Total</b></tr>";

        $i=0;
        
        foreach($_SESSION['panier_ref'] as $ref)
        {                       
            $pdoproduit = $pdo->query("SELECT * FROM produit WHERE pdt_ref='".$ref."'");
            foreach($pdoproduit as $row)
            {              
                $total=$row['pdt_prix']*(float)$_SESSION['panier_qte'][$i];
                $html.="<tr><td>".$row['pdt_ref']."<td>".$row['pdt_designation']."<td>".$row['pdt_prix']."<td>".$_SESSION['panier_qte'][$i]."<td>".$total.".</tr>";
            }                
            $i++;
        }

        $html.='</table><br><hr><br><form action="connexion.php" method="get">
            <table>
                <tr><td align="right">Nom<td> <input type="text" name="nom"></tr>
                <tr><td align="right">Mot de passe<td> <input type="password" name="mdp"></tr>
                <tr><td><td><input type="submit" name="comfirm" value="Commander"></tr>
            </table>
        </form>';
    }
    else
    {
        $html.="Votre panier est vide";
    }
    
}
catch(Exeption $e)
{
    echo "<p>ERREUR : ".$e->getMessage();
}

echo $html .="</body></html>";