<div class="container" style="border: 1px solid #eee; border-radius: 6px;">
    <div class="offset1">
        <h2>Sign in to Tarjeem</h2>
        <form action="<?= base_url('logins/validate') ?>" onsubmit="return formSubmit()" method="post" id="login_form">
            <div class="input-block-level">
                <p>Username:</p>
                <input type="text" name="login" class="input-append" />
                <p>Password:</p>
                <input type="password" name="password" class="input-append" />
                Forgot your <a href="<?= base_url() ?>logins/reset_password" >password?</a>
            </div>
            <button type="submit" class="btn">Sign in</button>     
        </form>
    </div>
</div>

<!--todo: username or email for login-->