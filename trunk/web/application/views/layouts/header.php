<!DOCTYPE html>
<head>
    <link href="<?php echo base_url(); ?>assets/css/bootstrap.css" rel="stylesheet">
</head>

<!-- Menu -->
<div class="navbar navbar-inverse navbar-fixed-top">
    <div class="navbar-inner">
        <div class="container">
            <ul class="nav pull-right">
                <?php if ($login['is_logged']) { ?>
                    <li><a href="<?= base_url('user/' . $login['alias_name']); ?>"><strong><?= $login['name'] ?></strong></a></li>
                <?php } ?>
                <li><a href="<?php echo base_url('/') ?>">Home</a></li>
                <?php if ($login['is_logged']) { ?>
                    <li><a href="<?php echo base_url('logout') ?>">Log Out</a></li>
                <?php } else { ?>
                    <li><a href="<?php echo base_url('login') ?>">Log In</a></li>
                    <li><a href="<?php echo base_url('signup') ?>">Sign Up</a></li>
                <?php } ?>
            </ul>            
        </div>
    </div>
</div>

<style>
    body {
        margin-top: 60px;
    }
</style>