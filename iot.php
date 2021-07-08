<?php
    // IMPORT CONFIG
    require("config.php");
    // READ GET
    $humedad = mysqli_real_escape_string($con, $_GET['humedad']);
    $temperatura = mysqli_real_escape_string($con, $_GET['temperatura']);
    // Instrucción para insertar los valores
    $query = "INSERT INTO datos(humedad,temperatura) VALUES('$humedad','$temperatura')";
    echo $humedad;
    echo $temperatura;
    // EJECT INTRUCTIONS
    mysqli_query($con, $query);
    mysqli_close($con);
?>