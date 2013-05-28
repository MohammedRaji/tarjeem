<div class="container">
<?php if ($user['is_logged']) { ?>    
    <h1>User <?= $user['name'] ?>, Logged as <?= $user['name'] ?></h1>
<?php } else { ?>    
    <h1>User <?= $user['name'] ?></h1>
<?php } ?>  
</div>