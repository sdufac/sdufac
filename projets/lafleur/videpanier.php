<?php

session_start();

$_SESSION['panier_qte']=array();
$_SESSION['panier_ref']=array();

header('Location: panier.php');