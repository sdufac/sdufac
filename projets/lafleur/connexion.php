<?php

session_start();

$html = <<<HTML
<html>
<head>
<title>Bulbes</title>
</head>
<body>
HTML;

if(isset($_GET['nom']) && isset($_GET['mdp']))
{
    if(!empty($_GET['nom']) && !empty($_GET['mdp']))
    {
        try
        {
            $bdo = new PDO("mysql:host=localhost;dbname=lafleur","root","");

            $time=time();
            $date=date("Y-m-d");
            $i=0;

            $client=$bdo->query("SELECT * FROM clientconnu WHERE clt_nom='".$_GET['nom']."';");

            foreach($client as $row)
            {
                if($row['clt_motPasse']==$_GET['mdp'])
                {
                    $bdo->query("INSERT INTO commande VALUES ('".$time."','".$row['clt_code']."','".$date."')");
                    foreach($_SESSION['panier_ref'] as $ref)
                    {
                        $descpdt=$bdo->query("SELECT pdt_designation FROM produit WHERE pdt_ref='".$ref."';");
                        foreach($descpdt as $desc)
                        {
                            $bdo->query("INSERT INTO contenir VALUES ('".$time."','".$row['clt_code']."','".$desc['pdt_designation']."','".$_SESSION['panier_qte'][$i]."');");

                        }
                        $i++;                       
                    }
                    $html.='Commande enregistré avec succés';        
                }
                else
                {
                    $html.='Impossible de se connecter';    
                }
            }
        }
        catch(Exeption $e)
        {
            echo "<p>ERREUR : ".$e->getMessage();
        }        
    }
}
echo $html.='</body></html>';