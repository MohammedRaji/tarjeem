<?php

function phpmailer_send($param = array(), $ishtml = false) {
	/* $param = array(
	 *   'from'     => '',
	 *   'fromname' => '',
	 *   'to'       => '',
	 *   'subject'  => '',
	 *   'message'  => ''
	 * );
	 */

	$param['from']     = isset($param['from'])     ? $param['from']     : MAIL_FROM;
	$param['fromname'] = isset($param['fromname']) ? $param['fromname'] : MAIL_FROMNAME;
	$param['debug']    = isset($param['debug'])    ? $param['debug']    : FALSE;

	require_once APPPATH . 'libraries/phpmailer/class.phpmailer.php';

	$mail = new PHPMailer();
	$mail->IsSMTP();
	$mail->Host       = MAIL_HOST;
	$mail->Port       = MAIL_PORT;
	$mail->SMTPAuth   = MAIL_AUTH;
	$mail->SMTPSecure = MAIL_SECURE;
	$mail->SMTPDebug  = $param['debug'];
	$mail->Username   = MAIL_USERNAME;
	$mail->Password   = MAIL_PASSWORD;
	$mail->From       = $param['from'];
	$mail->FromName   = $param['fromname'];
	$mail->CharSet    = 'UTF-8';
	if(isset($param['attachment']))
		$mail->AddAttachment($param['attachment']);
	
	if(is_array($param['to'])) {
		foreach($param['to'] as $a_to) {
			$mail->AddAddress($a_to, '');
		}
	} else {
		$mail->AddAddress($param['to'], '');
	}
	if(isset($param['cc'])){
	if(is_array($param['cc'])) {
		foreach($param['cc'] as $a_cc) {
			$mail->AddCC($a_cc, '');
		}
	} else {
		$mail->AddCC($param['cc'], '');
	}
	}
	
	$mail->AddReplyTo($mail->From, $mail->FromName);
	$mail->WordWrap = MAIL_WORDWRAP;
	$mail->IsHTML($ishtml);
	
	$mail->Subject = $param['subject'];
	$mail->Body    = $param['message'];
	
	return $mail->Send();
}