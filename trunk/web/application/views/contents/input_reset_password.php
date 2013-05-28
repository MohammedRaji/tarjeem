<div class="container" style="border: 2px solid #cbd3db; border-radius: 6px;">
    <div class="offset1">
        <h2>New password</h2>
        <form action="<?= base_url('signups/input_reset_handler') ?>" onsubmit="return formSubmit()" method="post" id="signup_form">
            <div class="input-block-level">
                <p>New Password:</p>
                <input id="password" type="password" name="password" class="input-append" />
                <span id="password-error" style="display: none"><img src="<?= base_url('assets/img/error.gif') ?>" alt="Name Error"><font color="red">Password cannot be blank!</font></span>
                <span id="password-ok" style="display: none"><img src="<?= base_url('assets/img/ok.gif') ?>" alt="Name Error"><font color="green">Password is ok.</font></span>
                <p>Retype New Password:</p>
                <input id="retype-password" type="password" name="retype_password" class="input-append" />
                <input type="hidden" name="user_id" value="<?= $user_reset['id'] ?>" />
                <span id="password-match" style="display: none"><img src="<?= base_url('assets/img/ok.gif') ?>" alt="Name Error"><font color="green">Password match</font></span>
                <span id="password-unmatch" style="display: none"><img src="<?= base_url('assets/img/error.gif') ?>" alt="Name Error"><font color="red">Password is unmatch!</font></span>
            </div>
            <button type="submit" class="btn">Reset Password</button>
        </form>
    </div>
</div>

<script type="text/javascript" src="<?= base_url('assets/js') ?>/jquery.js"></script>
<script type="text/javascript">
    
    var valid = false;
    
    function formSubmit()
    {        
        return valid;
    }
    
    $(document).ready(function() {     

        $('#password').blur(function(){   
            if($('#password').val() == '')
            {
                valid = false;
                $('#password-error').show();
                $('#password-ok').hide();
            } 
            else
            {
                valid = true;
                $('#password-error').hide();
                $('#password-ok').show();                    
            }
        });
        
        $('#retype-password').blur(function(){           
            var password = $('#password').val();
            var retype = $('#retype-password').val();
            if(password == retype)
            {
                valid = true;
                $('#password-match').show();
                $('#password-unmatch').hide();
            } 
            else
            {
                valid = false;
                $('#password-match').hide();
                $('#password-unmatch').show();                    
            }
        });
    });
    
</script>
