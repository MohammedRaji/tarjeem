<div class="container">
<?php if ($user['is_logged']) { ?>    
    <h1>Home, Logged as <?= $user['name'] ?></h1>
<?php } else { ?>    
    <h1>Home</h1>
<?php } ?>    
</div>