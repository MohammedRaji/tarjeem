<?php

/**
 * User Controller
 * This controller fully demonstrates the user class.
 *
 * @package User
 * @author Waldir Bertazzi Junior
 * @link http://waldir.org/
 * */
class Signups extends MY_Controller {

    function __construct() {
        parent::__construct();

        // Load the Library
        $this->load->library(array('login', 'login_manager','bcrypt'));
        $this->load->model('signup');
    }

    function index() {
        // Loads the signup view
        $data['title'] = "Sign Up";
        $data['content'] = 'contents/signup';
        $data['user'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }

    function is_email_used() {
        $get_result = $this->signup->check_email_availablity();

        if (!$get_result)
            echo 1;
        else
            echo 0;
    }

    function signup_handler() {

        foreach ($_POST as $attr => $val) {
            if (!isset($_POST[$attr]) || empty($_POST[$attr])) {
                redirect(base_url('signup/2#'));
            }
        }

        $token = $this->signup->get_token();
        $name = $this->input->post('fullname');
        $email = $this->input->post('email');
        $login = $this->input->post('login');
        $password = $this->input->post('password');

        $new_user_id = $this->login_manager->save_user($name, $login, $password, $email, 0, 1, $token);

        $mail_param = array(
            'from' => MAIL_FROM,
            'fromname' => MAIL_FROMNAME,
            'to' => $email,
            'subject' => 'Tarjeem Registration!',
            'message' => "<h1>Assalamu'alaikum " . $name . "!</h1><p>please verify your account, click the link below:</p>" . base_url('signups/validate/' . $token),
            'debug' => false,
        );
        $this->load->helper('phpmailer');
        phpmailer_send($mail_param, true);

        redirect(base_url('signups/post'));
    }

    function validate($token) {
        $result = $this->signup->validate($token);
        if ($result['valid']) {
            $data['user'] = $this->get_login_info();
            $this->validation(true);
        } else {
            $this->validation(false);
        }
    }

    function post() {
        $data['title'] = "Home";
        $data['content'] = 'contents/signup_success';
        $data['user'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }

    function validation($valid) {
        if ($valid) {
            $data['title'] = "Validation";
            $data['content'] = 'contents/validation_success';
            $data['user'] = $this->get_login_info();
            $this->load->view('layouts/master', $data);
        } else {
            $data['title'] = "Validation";
            $data['content'] = 'contents/validation_error';
            $data['user'] = $this->get_login_info();
            $this->load->view('layouts/master', $data);
        }
    }

    function retry($error_type) {
        if ($error_type == 1) {
            $data['error_message'] = 'Please fill all required fields';
        } else if ($error_type == 2) {
            $data['error_message'] = 'Username not available';
        }

        $data['title'] = "Sign Up";
        $data['content'] = 'contents/signup_error';
        $data['user'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }
    
    function reset_handler(){
        $token = $this->signup->get_token();
        $email = $this->input->post('email');
        
        $this->signup->update_by_email($email, $token);

        $mail_param = array(
            'from' => MAIL_FROM,
            'fromname' => MAIL_FROMNAME,
            'to' => $email,
            'subject' => 'Tarjeem Reset Password',
            'message' => "<h1>Assalamu'alaikum " . $name . "!</h1><p>If you would like to reset your password, please click the link below:</p>" . base_url('signups/reset_password/' . $token),
            'debug' => false,
        );
        $this->load->helper('phpmailer');
        phpmailer_send($mail_param, true);

        redirect(base_url('signups/post'));
    }
    
    function reset_password($token) {
        $user_reset = $this->signup->get_by_token($token);
          // Loads the signup view
        $data['title'] = "Sign Up";
        $data['content'] = 'contents/input_reset_password';
        $data['user'] = $this->get_login_info();
        $data['user_reset'] = $user_reset;
        $this->load->view($this->layout, $data);
    }
    
    function input_reset_handler(){
        $id = $this->input->post('user_id');
        $password = $this->input->post('password');
        $hashed_password = $this->bcrypt->hash($password);
        $this->signup->update_user($id, $hashed_password);
        redirect(base_url('signups/post'));
    }

}

?>
