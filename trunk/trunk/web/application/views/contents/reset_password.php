<script>
    var baseUrl = '<?= base_url() ?>';
</script>
<div class="container" style="border: 2px solid #cbd3db; border-radius: 6px;">
    <div class="offset1">
        <h2><?= $title ?></h2>
        <form action="<?= base_url('signups/reset_handler') ?>" onsubmit="return formSubmit()" method="post" id="reset_form">
            <div class="input-block-level"> 
                <p>Email:</p>
                <input id="email" type="text" name="email" class="input-append" />
                <span id="email-loading"><img src="<?= base_url('assets/img/loading.gif') ?>" alt="Ajax Indicator"></span>
                <span id="email-error"><img src="<?= base_url('assets/img/error.gif') ?>" alt="Name Error"><font color="red">Email cannot be blank!</font></span>
                <span id="email-ok"><img src="<?= base_url('assets/img/ok.gif') ?>" alt="Name Error"><font color="green">We will sent you reset confirmation.</font></span>
                <span id="email-response"></span>
            </div>
            <button type="submit" class="btn">Reset Password</button>
        </form>
    </div>
</div>

<script type="text/javascript" src="<?= base_url('assets/js') ?>/jquery.js"></script>
<script type="text/javascript">
    function formSubmit()
    {
        var valid = true;
        email = $('input[name=email]').val();
        
        if(email == ''){
            valid = false; $('#email-error').show();
            valid = true; $('#email-ok').hide();
        } else {
            valid = false; $('#email-error').hide();
            valid = true; $('#email-ok').show();
        }
        
        return valid;
        //document.getElementById("signup_form").submit();
    }
    
    $(document).ready(function() {
              
        /// make loader hidden in start
        $('#login-loading').hide();        
        $('#name-loading').hide();        
        $('#email-loading').hide();        
        $('#password-loading').hide();        
        $('#login-error').hide();        
        $('#name-error').hide();        
        $('#email-error').hide();        
        $('#password-error').hide();        
        $('#login-ok').hide();        
        $('#name-ok').hide();        
        $('#email-ok').hide();        
        $('#password-ok').hide();        

        $('#email').blur(function(){           
            var a = $("#email").val();
            var filter = /^[a-zA-Z0-9]+[a-zA-Z0-9_.-]+[a-zA-Z0-9_-]+@[a-zA-Z0-9]+[a-zA-Z0-9.-]+[a-zA-Z0-9]+.[a-z]{2,4}$/;
            // check if email is valid
            if(filter.test(a)){
                // show loader 
                $('#email-loading').show();
                $.post(baseUrl+"signups/is_email_used",{
                    email: $('#email').val()
                }, function(response){
                    if(!response){
                        $('#email-response').text('Wrong Email');
                    }
                    //#emailInfo is a span which will show you message
                    console.log('respon = ', response);
                    $('#email-loading').hide();
                });
                return false;
            }
        });
    });
</script>
