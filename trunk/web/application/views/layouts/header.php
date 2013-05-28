<!DOCTYPE html>
<head>
    <link href="<?php echo base_url(); ?>assets/css/bootstrap.css" rel="stylesheet">
    <link href="<?php echo base_url(); ?>assets/css/custom.css" rel="stylesheet">
    <link href="<?php echo base_url(); ?>assets/css/flat-ui.css" rel="stylesheet">
    <title><?= $title ?></title>
</head>

<!-- Menu -->
<div class="navbar navbar-inverse navbar-fixed-top">
    <div class="navbar-inner">
        <div class="container">
            <ul class="nav pull-right">
                <?php if ($user['is_logged']) { ?>
                    <li><a href="<?= base_url('user/' . $user['id']); ?>"><strong><?= $user['name'] ?></strong></a></li>
                <?php } ?>
                <li><a href="<?php echo base_url('/') ?>">Home</a></li>
                <?php if ($user['is_logged']) { ?>
                    <li><a href="<?php echo base_url('logout') ?>">Log out</a></li>
                <?php } else { ?>
                    <li><a href="<?php echo base_url('signup') ?>">Sign up</a></li>
                    <li class="dropdown">
                        <a class="dropdown-toggle" href="#" data-toggle="dropdown">Sign In <strong class="caret"></strong></a>
                        <div class="dropdown-menu" style="padding: 15px; padding-bottom: 0px;"> 
                            <form action="<?= base_url('logins/validate') ?>" method="post" id="login_form">
                                <div class="input-block-level">
                                    <p>Username:</p>
                                    <input type="text" name="login" class="input-append" />
                                    <p>Password:</p>
                                    <input type="password" name="password" class="input-append" />
                                </div>
                                <div>
                                    <span><a href="<?= base_url() ?>logins/reset_password" >Forgot Password?</a></span>
                                    <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<button type="submit" class="btn">Sign in</button></span>    
                                </div>
                            </form>
                        </div>
                    </li>
                <?php } ?>
            </ul>            
        </div>
    </div>
</div>

<script type="text/javascript" src="<?= base_url('assets/js') ?>/jquery.js"></script>
<script type="text/javascript" src="<?= base_url('assets/js') ?>/bootstrap.min.js"></script>
<script language="javascript">
    $('.dropdown-toggle').dropdown();
    $('.dropdown-menu').find('form').click(function (e) {
        e.stopPropagation();
    });
</script>

<style>
    body {
        margin-top: 60px;
    }
</style>