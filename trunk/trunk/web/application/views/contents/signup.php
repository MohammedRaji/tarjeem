<div class="container" style="border: 2px solid #cbd3db; border-radius: 6px;">
    <div class="offset1">
        <h2>Join Tarjeem today.</h2>
        <form action="<?= base_url('signups/signup_handler') ?>" onsubmit="return formSubmit()" method="post" id="signup_form">
            <div class="input-block-level">
                <p><strong>Full name:</strong></p>
                <input id="name" type="text" name="fullname" class="input-append span5" />
                <span id="name-loading" style="display: none;"><img src="<?= base_url('assets/img/loading.gif') ?>" alt="Ajax Indicator"></span>
                <span id="name-error" style="display: none;"><img src="<?= base_url('assets/img/error.gif') ?>" alt="Name Error"></span>
                <span id="name-ok" style="display: none;"><img src="<?= base_url('assets/img/ok.gif') ?>" alt="Name Error"></span>
                <span id="name-response-ok" style="color: green; display: none;">Name looks great.</span>
                <span id="name-response-empty-error" style="color: red; display: none;">A name is required!</span>
                <p><strong>Email address:</strong></p>
                <input id="email" type="text" name="email" class="input-append span5" placeholder="example@example.com"/>
                <span id="email-loading" style="display: none;"><img src="<?= base_url('assets/img/loading.gif') ?>" alt="Ajax Indicator"></span>
                <span id="email-error" style="display: none;"><img src="<?= base_url('assets/img/error.gif') ?>" alt="Name Error"></span>
                <span id="email-ok" style="display: none; color: green;"><img src="<?= base_url('assets/img/ok.gif') ?>" alt="Name Error"></span>
                <span id="email-response-ok" style="color: green; display: none;">We will email you a confirmation.</span>
                <span id="email-response-empty-error" style="color: red; display: none;">Email cannot be blank!</span>
                <span id="email-response-valid-error" style="color: red; display: none;">Doesn't looks like a valid email!</span>
                <span id="email-response-used-error" style="color: red; display: none;">Email is already used!</span>
                <p><strong>Create a password:</strong></p>
                <input id="password" type="password" name="password" class="input-append span5" />
                <span id="password-loading" style="display: none;"><img src="<?= base_url('assets/img/loading.gif') ?>" alt="Ajax Indicator"></span>
                <span id="password-error" style="display: none;"><img src="<?= base_url('assets/img/error.gif') ?>" alt="Name Error"></span>
                <span id="password-ok" style="display: none;"><img src="<?= base_url('assets/img/ok.gif') ?>" alt="Name Error"></span>
                <span id="password-response-ok" style="color: green; display: none;">Password is ok.</span>
                <span id="password-response-empty-error" style="color: red; display: none;">Password cannot be blank!</span>            
                <span id="password-response-size-error" style="color: red; display: none;">Password must at least 6 character!</span>            
                <p><strong>Choose your username:</strong></p>
                <input id="login" type="text" name="login" class="input-append span5" />
                <span id="login-loading" style="display: none;"><img src="<?= base_url('assets/img/loading.gif') ?>" alt="Ajax Indicator"></span>
                <span id="login-error" style="display: none;"><img src="<?= base_url('assets/img/error.gif') ?>" alt="Name Error"></span>
                <span id="login-ok" style="display: none;"><img src="<?= base_url('assets/img/ok.gif') ?>" alt="Name Error"></span>
                <span id="login-response-ok" style="color: green; display: none;">Username is ok.</span>
                <span id="login-response-empty-error" style="color: red; display: none;">Username cannot be blank!</span>            
                <span id="login-response-taken-error" style="color: red; display: none;">This username is already taken!</span>            
            </div>
            <p>By clicking button, you aggre to the Tarjeem <a href="<?= base_url('term') ?>">term and service</a></p>
            <button type="submit" class="btn">Create my account</button>
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

        $('#name').blur(function(){           
            if($('#name').val() == ''){            
                $('#name-error').show(); 
                $('#name-ok').hide();
                $('#name-response-ok').hide();
                $('#name-response-empty-error').show();
                valid = false; 
            } else {
                $('#name-error').hide(); 
                $('#name-ok').show();
                $('#name-response-ok').show();
                $('#name-response-empty-error').hide();
                valid = true; 
            }
        });
    
        $('#password').blur(function(){           
            if($('#password').val() == ''){            
                $('#password-error').show(); 
                $('#password-ok').hide();
                $('#password-response-ok').hide();
                $('#password-response-empty-error').show();
                valid = false; 
            } else {
                $('#password-error').hide(); 
                $('#password-ok').show();
                $('#password-response-ok').show();
                $('#password-response-empty-error').hide();
                valid = true; 
            }
        });
        
        $('#email').blur(function(){           
            var a = $("#email").val();
            var filter = /^[a-zA-Z0-9]+[a-zA-Z0-9_.-]+[a-zA-Z0-9_-]+@[a-zA-Z0-9]+[a-zA-Z0-9.-]+[a-zA-Z0-9]+.[a-z]{2,4}$/;
            // check if email is valid
            if(filter.test(a)){
                // show loader 
                $('#email-loading').show();
                $.post("signups/is_email_used", { email: $('#email').val() }, function(response) {
                    
                    $('#email-response-valid-error').hide();              

                    if(!response)
                    {
                        $('#email-ok').hide(); 
                        $('#email-error').show(); 
                        $('#email-response-ok').hide();
                        $('#email-response-used-error').show();
                        valid = false; 
                    } 
                    else
                    {
                        $('#email-ok').show(); 
                        $('#email-error').hide(); 
                        $('#email-response-ok').show();
                        $('#email-response-used-error').hide();  
                        valid = true; 
                    }
                    $('#email-loading').hide();
                });
                return false;
            } 
            else
            {
                $('#email-ok').hide(); 
                $('#email-error').show(); 
                $('#email-response-valid-error').show();              
                valid = false; 
            }
        });

    });
</script>
